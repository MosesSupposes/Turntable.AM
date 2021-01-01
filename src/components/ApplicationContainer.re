open UsePage;

[@react.component]
let make =
    (
      ~page: Page.t,
      ~setPage: (Page.t => Page.t) => unit,
      ~accessToken: option(string),
    ) => {
  switch (page) {
  | Page.Home => <Home setPage accessToken />
  | Page.UserProfile => <UserProfile setPage />
  | Page.Login => <Login />
  };
};
