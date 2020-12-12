let handleSignIn = () => {
  SpotifyAPI.Authorization.signIn() |> ignore;
};

[@react.component]
let make = () => {
  <div>
    <p> {React.string("Sign in to your Spotify Account")} </p>
    <button onClick={_ => handleSignIn()}> {React.string("Sign In")} </button>
  </div>;
};
