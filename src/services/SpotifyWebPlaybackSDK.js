import React from "react";

const createEventHandlers = (player) => {
  player.on("initialization_error", (e) => {
    console.error(e);
  });
  player.on("authentication_error", (e) => {
    alert(
      "You must sign back in to your Spotify account to resume the music player."
    );
    console.error(e);
  });
  player.on("account_error", (e) => {
    console.error(e);
  });
  player.on("playback_error", (e) => {
    console.error(e);
  });

  // Playback status updates
  player.on("player_state_changed", (state) => {
    console.log(state);
  });

  player.on("ready", ({ device_id }) => {
    console.log("Let the music play on!");
  });
};

const startPlayer = (accessToken) => {
  window.onSpotifyWebPlaybackSDKReady = () => {
    const player = new Spotify.Player({
      name: "Turntable.AM",
      getOAuthToken: (callback) => callback(accessToken),
      volume: 1.0,
    });

    createEventHandlers(player);

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
