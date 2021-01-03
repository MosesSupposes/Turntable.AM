import React from "react";

const createEventHandlers = (player) => {
  player.on("initialization_error", (e) => {
    console.error(e);
  });
  player.on("authentication_error", (e) => {
    alert(
      'You must sign back in to your Spotify account to resume the music player. Click the "Sign In" link above.'
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
      volume: 0.8,
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

function SpotifyPlayer(accessToken) {
  const [state, setState] = React.useState({
    token: "",
    deviceId: "",
    error: "",
    trackName: "",
    artistName: "",
    albumName: "",
    playing: false,
    position: 0,
    duration: 0,
    player: {},
  });

  const createEventHandlers = () => {
    state.player.on("initialization_error", (e) => console.error(e));
    // TODO: Set the page to the sign in page so the user can log back in.
    state.player.on("authentication_error", (e) => console.error(e));
    state.player.on("account_error", (e) => console.error(e));
    state.player.on("playback_error", (e) => console.error(e));

    state.player.on("player_state_changed", (state) => console.log(state));

    state.player.on("ready", (data) => {
      const { device_id } = data;
      console.log("Let the music play on!");
      setState((prevState) => ({ ...prevState, deviceId: device_id }));
    });
  };

  let playerCheckInterval;

  const checkForPlayer = () => {
    let accessToken =
      "BQDrvW_sGnbH4SHs_zMv5POZbwi7kX1ojjFVSTEKkOiZ4_Hna2CPo0nmL1tijfHGkky86h2iRidU45pJ3OBXUJfdss4zpVKncJbWC0gz0ARbGGvjphd4HHQd4EnK7z3tA8mH9lA565nxG0Xr0bpQh0Jt6pGM1UDdAWvXes_yZhgsM_xhIn4";
    if (window.Spotify != null) {
      clearInterval(playerCheckInterval);
      setState((prevState) => ({
        ...prevState,
        player: new window.Spotify.Player({
          // TODO: Capture the user's name and use it here
          name: "Moses' Spotify Player",
          getOAuthToken: (cb) => cb(accessToken),
        }),
      }));
      createEventHandlers();
      state.player.connect();
    }
  };

  // Start the Spotify Player once it's been mounted onto the DOM
  React.useEffect(() => {
    playerCheckInterval = setInterval(() => checkForPlayer(), 1000);
  }, []);

  return (
    <div>
      <h2>Now playing</h2>
      {state.error && <p>Error: {state.error}</p>}
      <div>
        <p>Artist: {state.artistName}</p>
        <p>Track: {state.trackName}</p>
        <p>Album: {state.albumName}</p>
      </div>
    </div>
  );
}

export default startPlayer;
//export default SpotifyPlayer;
