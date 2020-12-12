open UsePage;

[@react.component]
let make = (~to_: Page.t, ~setPage) => {
  <div onClick={_ => setPage(_ => to_)} />;
};
