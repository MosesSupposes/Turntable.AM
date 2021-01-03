[@bs.val] external window: Js.t({..}) = "window";
[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";

type musicPlayerState('a) = {
  currentTrack: string,
  currentArtist: string,
  currentAlbum: string,
  spotifyPlayer: option(Js.t({..} as 'a)),
};

// TODO: Decode the spotifyPlayer object into a record
// TODO: Finish the rest of the tutorial to figure out how to enable automatic playback
[@react.component]
let make = () => {
  let (musicPlayer: musicPlayerState({..}), setMusicPlayer) =
    React.useState(() =>
      {
        currentTrack: "",
        currentArtist: "",
        currentAlbum: "",
        spotifyPlayer: None,
      }
    );

  // Store the Spotify player object in state once it loads
  let () =
    React.useEffect0(() => {
      let () =
        setTimeout(
          () => {
            setMusicPlayer(prevState =>
              {...prevState, spotifyPlayer: Some(window##player)}
            )
          },
          1000,
        );
      None;
    });
  let {currentTrack, currentArtist, currentAlbum, spotifyPlayer} = musicPlayer;
  <div>
    <h2> {React.string("Now Playing:")} </h2>
    <p> {React.string({j|Track: $currentTrack |j})} </p>
    <p> {React.string({j|Artist: $currentArtist|j})} </p>
    <p> {React.string({j|Album: $currentAlbum|j})} </p>
  </div>;
};
