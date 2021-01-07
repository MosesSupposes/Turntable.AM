[@bs.val] external window: Js.t({..}) = "window";
[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";

[%bs.raw {|require("../styles/musicPlayer.css")|}];

open UsePage;

type spotifyPlayer('a) = Js.t({..} as 'a);

type musicPlayerState('a) = {
  currentTrack: string,
  currentArtist: string,
  currentAlbum: string,
  nextSong: string,
  nextArtist: string,
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
    | [firstArtist, ...otherArtists] => firstArtist.name
    };
  };

  let getCurrentArtist = (trackInfo: Decoders.MusicPlayer.trackInfo) => {
    trackInfo.track_window.current_track.artists |> getArtistOrUnknown;
  };

  let getCurrentAlbum = (trackInfo: Decoders.MusicPlayer.trackInfo): string => {
    trackInfo.track_window.current_track.album.name;
  };

  let getNextSong = (trackInfo: Decoders.MusicPlayer.trackInfo): string => {
    trackInfo.track_window.next_tracks |> List.hd |> (x => x.name);
  };

  let getNextArtist = (trackInfo: Decoders.MusicPlayer.trackInfo): string => {
    trackInfo.track_window.next_tracks
    |> List.hd
    |> (x => x.artists)
    |> getArtistOrUnknown;
  };

  let getAlbumCoverUrl = (images: list(Decoders.MusicPlayer.image)): string => {
    switch (images) {
    | [] => ""
    | [smallImg, mediumImg, largeImg, ...restImgs] => largeImg.url
    | [smallImg, mediumImg, ...restImgs] => mediumImg.url
    | [smallImg, ...restImgs] => smallImg.url
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
            currentTrack: getCurrentTrack(decodedTrackInfo),
            currentArtist: getCurrentArtist(decodedTrackInfo),
            currentAlbum: getCurrentAlbum(decodedTrackInfo),
            nextSong: getNextSong(decodedTrackInfo),
            nextArtist: getNextArtist(decodedTrackInfo),
          }
        );
      });
    ();
  };

  let renderLoadingScreen = () =>
    <p className="loading"> {React.string("Loading...")} </p>;

  let renderConnectionInstructions = () =>
    <p className="connection-instructions">
      {React.string(
         "To interact with the Music Player, navigate to Spotify from your web browser and click the \"Connect to a device\" button. Then, select \"Turntable.AM\" from the menu.",
       )}
    </p>;
};

module MediaControlCard = {
  [@bs.module "./MediaControlCard.js"] [@react.component]
  external make:
    (
      ~songTitle: string,
      ~artist: string,
      ~albumCoverUrl: string,
      ~albumName: string,
      ~player: Js.t({..}),
      ~isPaused: bool
    ) =>
    React.element =
    "default";
};

// TODO: Finish the tutorial to figure out how to enable automatic playback
// TODO: Add player controls (ex: pause, skip track, etc.)
// TODO: Render the pause icon when the music is playing and the play icon when the music is paused
// TODO: Set breakpoints for the music player
[@react.component]
let make = (~setPage: (Page.t => Page.t) => unit) => {
  let (musicPlayer: musicPlayerState({..}), setMusicPlayer) =
    React.useState(() =>
      {
        currentTrack: "",
        currentArtist: "",
        currentAlbum: "",
        nextSong: "",
        nextArtist: "",
        deviceId: None,
        spotifyPlayer: None,
        trackInfo: None,
      }
    );

  let {
    currentTrack,
    currentArtist,
    currentAlbum,
    nextSong,
    nextArtist,
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
      | Some(player) =>
        Helpers.createEventHandlers(player, setPage, setMusicPlayer)
      | None => ()
      };
      None;
    },
    [|spotifyPlayer|],
  );
  switch (spotifyPlayer) {
  | Some(player) =>
    switch (trackInfo) {
    | Some(info) =>
      let {
        paused,
        track_window: {current_track: {album: {images: albumCovers}}},
      }: Decoders.MusicPlayer.trackInfo = info;
      let albumCoverUrl = albumCovers |> Helpers.getAlbumCoverUrl;
      <div>
        <h2> {React.string("Now Playing:")} </h2>
        <div className="media-control-card-container">
          <MediaControlCard
            songTitle=currentTrack
            artist=currentArtist
            albumCoverUrl
            albumName=currentAlbum
            player
            isPaused=paused
          />
        </div>
        <p> {React.string({j|Up Next: $nextSong by $nextArtist|j})} </p>
      </div>;
    | None => Helpers.renderConnectionInstructions()
    }
  | None => Helpers.renderLoadingScreen()
  };
};
