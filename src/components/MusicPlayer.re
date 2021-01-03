type musicPlayerState = {
  currentTrack: string,
  currentArtist: string,
  currentAlbum: string,
};

[@react.component]
let make = () => {
  let (musicPlayer, setMusicPlayer) =
    React.useState(() =>
      {currentTrack: "", currentArtist: "", currentAlbum: ""}
    );
  let {currentTrack, currentArtist, currentAlbum} = musicPlayer;
  <div>
    <h2> {React.string("Now Playing:")} </h2>
    <p> {React.string({j|Track: $currentTrack |j})} </p>
    <p> {React.string({j|Artist: $currentArtist|j})} </p>
    <p> {React.string({j|Album: $currentAlbum|j})} </p>
  </div>;
};
