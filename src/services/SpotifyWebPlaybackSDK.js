const startPlayer = (accessToken) => {
  window.onSpotifyWebPlaybackSDKReady = () => {
    const play = ({
      spotify_uri,
      playerInstance: {
        _options: { getOAuthToken, id },
      },
    }) => {
      fetch(`https://api.spotify.com/v1/me/player/play?device_id=${id}`, {
        method: "PUT",
        body: JSON.stringify({ uris: [spotify_uri] }),
        headers: {
          "Content-Type": "application/json",
          Authorization: `Bearer ${accessToken}`,
        },
      });
    };

    play({
      playerInstance: new Spotify.Player({ name: "Moses' Awesome Playlist" }),
      spotify_uri: "spotify:track:7xGfFoTpQ2E7fRF5lN10tr",
    });
  };
};

export default startPlayer;
