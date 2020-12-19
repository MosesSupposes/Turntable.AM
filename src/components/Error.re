[@react.component]
let make = (~message: string) => {
  <div> {React.string(message)} </div>;
};
