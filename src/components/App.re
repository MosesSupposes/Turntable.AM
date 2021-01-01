[@bs.val] external document: Js.t({..}) = "document";

[@react.component]
let make = () => {
  let {page, setPage}: UsePage.export = UsePage.make();
  let (accessToken, setAccessToken) = React.useState(() => None);

  React.useEffect0(() => {
    let accessToken = ParseUrl.getAccessToken(document##location##href);
    setAccessToken(_ => accessToken);

    let future =
      switch (accessToken) {
      | Some(token) =>
        SpotifyAPI.Search.searchArtist(
          ~accessToken=token,
          ~artist="Future",
          ~onSuccess=future => Js.Promise.resolve(Js.log(future)),
          ~onFail=error => Js.Promise.resolve(Js.log(error)),
        )
      | None => Js.Promise.resolve()
      };

    let moneyLonger =
      switch (accessToken) {
      | Some(token) =>
        SpotifyAPI.Search.searchTrack(
          ~accessToken=token,
          ~track="money%20longer",
          ~onSuccess=
            tracksPromise => {
              Js.log(tracksPromise);
              tracksPromise;
            },
          ~onFail=
            error => {
              Js.log(error);
              Js.Promise.resolve();
            },
        )
      | None =>
        exception MissingAccessToken;
        Js.Promise.reject(MissingAccessToken);
      };
    None;
  });
  <main>
    <Header setPage />
    <ApplicationContainer page setPage accessToken />
    <Footer />
  </main>;
};
