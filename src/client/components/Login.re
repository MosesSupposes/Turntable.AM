let handleSignInPKCE = () => {
  SpotifyAPI.AuthorizationPKCE.signIn() |> ignore;
};

let handleSignInImplicitGrant = () =>
  SpotifyAPI.AuthorizationImplicitGrant.signIn() |> ignore;

[@react.component]
let make = () => {
  <div>
    <p> {React.string("Sign in to your Spotify Account")} </p>
    <button onClick={_ => handleSignInPKCE()}>
      {React.string("Sign In PKCE")}
    </button>
    <button onClick={_ => handleSignInImplicitGrant()}>
      {React.string("Sign In Implicit Grant")}
    </button>
  </div>;
};
