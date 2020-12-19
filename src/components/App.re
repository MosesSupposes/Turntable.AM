[@bs.val] external document: Js.t({..}) = "document";

[@react.component]
let make = () => {
  let {page, setPage}: UsePage.export = UsePage.make();
  let (accessToken, setAccessToken) = React.useState(() => None);

  React.useEffect0(() => {
    let accessToken = ParseUrl.getAccessToken(document##location##href);
    setAccessToken(_ => accessToken);
    None;
  });

  <main>
    <Header setPage />
    <ApplicationContainer page setPage />
    <Footer />
  </main>;
};
