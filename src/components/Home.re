open UsePage;

// Don't render the welcome message and app description if the user has logged in to their Spotify account.
let shouldShowWelcomeMessageAndAppDescription =
    (accessToken: option(string)): bool => {
  switch (accessToken) {
  | Some(token) => false
  | None => true
  };
};

let renderWelcomeMessage = () =>
  <h1> {React.string("Welcome to Turntable.AM")} </h1>;

let renderAppDescription = () =>
  <p>
    {React.string(
       "Turntable.AM is a music sharing app that allows you to collaboratively create custom playlists with your friends. Click the Sign In link above to connect your Spotify account to the app.",
     )}
  </p>;

[@react.component]
let make = (~setPage: (Page.t => Page.t) => unit, ~accessToken) => {
  <div>
    {shouldShowWelcomeMessageAndAppDescription(accessToken)
       ? <div> {renderWelcomeMessage()} {renderAppDescription()} </div>
       : <div />}
  </div>;
};
