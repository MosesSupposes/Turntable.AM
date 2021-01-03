type token = string;

[@bs.module "../services/SpotifyWebPlaybackSDK.js"]
external startPlayer: token => unit = "default";

open UsePage;

// Don't render the welcome message and app description if the user has logged in to their Spotify account.
let shouldShowWelcomeMessageAndAppDescription =
    (accessToken: option(string)): bool => {
  switch (accessToken) {
  | Some(token) => false
  | None => true
  };
};

let renderWelcomeMessage: unit => React.element =
  () => <h1> {React.string("Welcome to Turntable.AM")} </h1>;

let renderAppDescription: unit => React.element =
  () =>
    <p>
      {React.string(
         "Turntable.AM is a music sharing app that allows you to collaboratively create custom playlists with your friends. Click the Sign In link above to connect your Spotify account to the app.",
       )}
    </p>;

[@react.component]
let make =
    (~setPage: (Page.t => Page.t) => unit, ~accessToken: option(string)) => {
  let () =
    React.useEffect1(
      () => {
        let () =
          switch (accessToken) {
          | Some(token) => startPlayer(token)
          | None => ()
          };
        None;
      },
      [|accessToken|],
    );

  <div>
    {shouldShowWelcomeMessageAndAppDescription(accessToken)
       ? <div> {renderWelcomeMessage()} {renderAppDescription()} </div>
       : <MusicPlayer />}
  </div>;
};
