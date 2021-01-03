import React from "react";

const startPlayer = (accessToken) => {
  window.onSpotifyWebPlaybackSDKReady = () => {
    const player = new Spotify.Player({
      name: "Turntable.AM",
      getOAuthToken: (callback) => callback(accessToken),
      volume: 1.0,
    });

    player.on("ready", ({ device_id }) => {
      window.deviceId = device_id;
      console.log("Let the music play on!");
    });

    player.connect().then((connectionWasSuccessful) => {
      if (connectionWasSuccessful) {
        console.log("The Web Playback SDK successfully connected to Spotify!");
      } else {
        console.log(
          "The Web Playback SDK was unsuccessful in trying to connect to Spotify."
        );
      }
    });
    window.player = player;
  };
};

export default startPlayer;
