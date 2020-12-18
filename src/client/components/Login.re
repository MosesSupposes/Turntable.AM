let handleSignInPKCE = () => SpotifyAPI.AuthorizationPKCE.signIn() |> ignore;

let handleSignInImplicitGrant = () =>
  SpotifyAPI.AuthorizationImplicitGrant.signIn() |> ignore;

let handleSignInClientCredentials = () =>
  SpotifyAPI.AuthorizationClientCredentials.signIn() |> ignore;

[@react.component]
let make = () => {
  <div>
    <p> {React.string("Sign in to your Spotify Account")} </p>
    <button onClick={_ => handleSignInPKCE()}>
      {React.string("Log in with Spotify PKCE")}
    </button>
    <button onClick={_ => handleSignInImplicitGrant()}>
      {React.string("Sign in with Spotify Implicit Grant")}
    </button>
    <button onClick={_ => handleSignInClientCredentials()}>
      {React.string("Log in with Spotify Client Credentials")}
    </button>
  </div>;
};
