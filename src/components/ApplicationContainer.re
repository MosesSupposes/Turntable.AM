open UsePage;

[@react.component]
let make = (~page: Page.t, ~setPage: (Page.t => Page.t) => unit) => {
  switch (page) {
  | Page.Home => <Home setPage />
  | Page.UserProfile => <UserProfile setPage />
  | Page.Login => <Login />
  };
};
