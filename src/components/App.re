[@bs.val] external document: Js.t({..}) = "document";

[@react.component]
let make = () => {
  let {page, setPage}: UsePage.export = UsePage.make();
  let (accessToken, setAccessToken) = React.useState(() => None);

  React.useEffect0(() => {
    let accessToken = ParseUrl.getAccessToken(document##location##href);
    setAccessToken(_ => accessToken);

    // TODO: Try another endpoint
    let futuresTracks =
      switch (accessToken) {
      | Some(token) =>
        SpotifyAPI.Search.searchArtist(~accessToken=token, ~artist="Future")
      | None => Js.Promise.resolve()
      };
    Js.log(futuresTracks);

    let moneyLonger =
      switch (accessToken) {
      | Some(token) =>
        SpotifyAPI.Search.searchTrack(
          ~accessToken=token,
          ~track="money%20longer",
        )
      | None => Js.Promise.resolve()
      };
    Js.log2("money longer", moneyLonger);
    None;
  });

  <main>
    <Header setPage />
    <ApplicationContainer page setPage />
    <Footer />
  </main>;
};
