open UsePage;

[@react.component]
let make = (~setPage: (Page.t => Page.t) => unit) => {
  <div> <h1> {React.string("Profile")} </h1> </div>;
};
