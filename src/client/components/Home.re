open UsePage;

[@react.component]
let make = (~setPage: (Page.t => Page.t) => unit) => {
  <div>
    <h1> {React.string("Welcome to Turntable.AM")} </h1>
    <p>
      {React.string(
         "Turntable.AM is a music sharing app that allows you to collaboratively create custom playlists with your friends. Click the Sign In link above to connect your Spotify account to the app.",
       )}
    </p>
  </div>;
};
