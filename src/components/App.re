[@bs.val] external document: Js.t({..}) = "document";

[@react.component]
let make = () => {
  let {page, setPage}: UsePage.export = UsePage.make();
  let (accessToken, setAccessToken) = React.useState(() => None);
  let (profile, setProfile) = React.useState(() => None);

  exception MissingAccessToken;

  let () =
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
        | None => Js.Promise.reject(MissingAccessToken)
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
        | None => Js.Promise.reject(MissingAccessToken)
        };

      let currentUser =
        switch (accessToken) {
        | Some(token) =>
          SpotifyAPI.Profile.getCurrentUsersProfile(token)
          |> Js.Promise.(
               then_(profile => {
                 let decodedProfile = Decoders.Profile.decodeUser(profile);
                 setProfile(_ => Some(decodedProfile));
                 resolve(decodedProfile);
               })
             )
        | None => Js.Promise.reject(MissingAccessToken)
        };
      None;
    });
  <main>
    <Header setPage />
    <ApplicationContainer page setPage accessToken />
    <Footer />
  </main>;
};
