[@bs.val] external window: Js.t({..}) = "window";
[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";

open UsePage;

type spotifyPlayer('a) = Js.t({..} as 'a);

type musicPlayerState('a) = {
  currentTrack: string,
  currentArtist: string,
  currentAlbum: string,
  deviceId: string,
  spotifyPlayer: option(spotifyPlayer({..} as 'a)),
};

let createEventHandlers =
    (player: spotifyPlayer({..}), setPage: (Page.t => Page.t) => unit): unit => {
  // The "ready" event is handled from the JS side (see src/services/SpotifyWebPlaybackSDK.js)
  let () = player##on("initialization_error", e => Js.log(e));
  let () = player##on("authentication_error", e => setPage(_ => Page.Login));
  let () = player##on("account_error", e => Js.log(e));
  let () = player##on("playback_error", e => Js.log(e));
  let () = player##on("player_state_changed", state => Js.log(state));
  ();
};

// TODO: Decode the spotifyPlayer object into a record
// TODO: Finish the rest of the tutorial to figure out how to enable automatic playback
[@react.component]
let make = (~setPage: (Page.t => Page.t) => unit) => {
  let (musicPlayer: musicPlayerState({..}), setMusicPlayer) =
    React.useState(() =>
      {
        currentTrack: "",
        currentArtist: "",
        currentAlbum: "",
        deviceId: "",
        spotifyPlayer: None,
      }
    );

  let {currentTrack, currentArtist, currentAlbum, spotifyPlayer} = musicPlayer;

  // Store the Spotify player object in state once it loads
  let () =
    React.useEffect0(() => {
      let () =
        setTimeout(
          () => {
            setMusicPlayer(prevState =>
              {
                ...prevState,
                spotifyPlayer: Some(window##player),
                deviceId: window##deviceId,
              }
            )
          },
          1000,
        );
      None;
    });

  React.useEffect1(
    () => {
      switch (spotifyPlayer) {
      | Some(player) => createEventHandlers(player, setPage)
      | None => ()
      };
      None;
    },
    [|spotifyPlayer|],
  );

  switch (spotifyPlayer) {
  | Some(player) =>
    <div>
      <h2> {React.string("Now Playing:")} </h2>
      <p> {React.string({j|Track: $currentTrack |j})} </p>
      <p> {React.string({j|Artist: $currentArtist|j})} </p>
      <p> {React.string({j|Album: $currentAlbum|j})} </p>
    </div>
  | None => <p> {React.string("Loading...")} </p>
  };
};
