[%bs.raw {|require("../styles/login.css")|}];
[@react.component]
let make = () => {
  <div className="login-container">
    <button>
      <a href=SpotifyAPI.Authorization.finalEncodedUri>
        {React.string("Log in with Spotify")}
      </a>
    </button>
  </div>;
};
