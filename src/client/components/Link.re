open UsePage;

[@react.component]
let make = (~to_: Page.t, ~setPage, ~children) => {
  <div onClick={_ => setPage(_ => to_)}> children </div>;
};
