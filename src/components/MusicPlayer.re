[@bs.val] external window: Js.t({..}) = "window";
[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";

open UsePage;

type spotifyPlayer('a) = Js.t({..} as 'a);

type musicPlayerState('a) = {
  currentTrack: string,
  currentArtist: string,
  currentAlbum: string,
  deviceId: option(string),
  spotifyPlayer: option(spotifyPlayer({..} as 'a)),
  trackInfo: option(Decoders.MusicPlayer.trackInfo),
};

// Helper functions
module Helpers = {
  let getCurrentTrack = (trackInfo: Decoders.MusicPlayer.trackInfo): string => {
    trackInfo.track_window.current_track.name;
  };
  let getArtistOrUnknown =
      (artists: list(Decoders.MusicPlayer.artist)): string => {
    switch (artists) {
    | [] => "Unknown"
    | [artist] => artist.name
    | [firstArtist, ...otherArtists] => firstArtist.name
    };
  };

  let getCurrentArtist = (trackInfo: Decoders.MusicPlayer.trackInfo) => {
    trackInfo.track_window.current_track.artists |> getArtistOrUnknown;
  };

  let getCurrentAlbum = (trackInfo: Decoders.MusicPlayer.trackInfo): string => {
    trackInfo.track_window.current_track.album.name;
  };
};

let createEventHandlers =
    (
      player: spotifyPlayer({..}),
      setPage: (Page.t => Page.t) => unit,
      setMusicPlayer:
        (musicPlayerState({..}) => musicPlayerState({..})) => unit,
    )
    : unit => {
  // The "ready" event is handled from the JS side (see src/services/SpotifyWebPlaybackSDK.js)
  let () = player##on("initialization_error", e => Js.log(e));
  let () = player##on("authentication_error", e => setPage(_ => Page.Login));
  let () = player##on("account_error", e => Js.log(e));
  let () = player##on("playback_error", e => Js.log(e));
  let () =
    player##on("player_state_changed", state => {
      let decodedTrackInfo = Decoders.MusicPlayer.decodeTrackInfo(state);
      setMusicPlayer(prevState =>
        {
          ...prevState,
          trackInfo: Some(decodedTrackInfo),
          currentTrack: Helpers.getCurrentTrack(decodedTrackInfo),
          currentArtist: Helpers.getCurrentArtist(decodedTrackInfo),
          currentAlbum: Helpers.getCurrentAlbum(decodedTrackInfo),
        }
      );
    });
  ();
};

let renderLoadingScreen = () => <p> {React.string("Loading...")} </p>;

// TODO: Render "Up Next" to the Music Player
// TODO: Finish the tutorial to figure out how to enable automatic playback
[@react.component]
let make = (~setPage: (Page.t => Page.t) => unit) => {
  let (musicPlayer: musicPlayerState({..}), setMusicPlayer) =
    React.useState(() =>
      {
        currentTrack: "",
        currentArtist: "",
        currentAlbum: "",
        deviceId: None,
        spotifyPlayer: None,
        trackInfo: None,
      }
    );

  let {
    currentTrack,
    currentArtist,
    currentAlbum,
    deviceId,
    spotifyPlayer,
    trackInfo,
  } = musicPlayer;

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
                deviceId: Some(window##deviceId),
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
      | Some(player) => createEventHandlers(player, setPage, setMusicPlayer)
      | None => ()
      };
      None;
    },
    [|spotifyPlayer|],
  );

  React.useEffect1(
    () => {
      switch (trackInfo) {
      | Some(info) => Js.log2("here", info)
      | None => ()
      };
      None;
    },
    [|trackInfo|],
  );

  switch (spotifyPlayer) {
  | Some(player) =>
    switch (trackInfo) {
    | Some(info) =>
      <div>
        <h2> {React.string("Now Playing:")} </h2>
        <p> {React.string({j|Track: $currentTrack |j})} </p>
        <p> {React.string({j|Artist: $currentArtist|j})} </p>
        <p> {React.string({j|Album: $currentAlbum|j})} </p>
      </div>
    | None => renderLoadingScreen()
    }
  | None => renderLoadingScreen()
  };
};
