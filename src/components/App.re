[@react.component]
let make = () => {
  let {page, setPage}: UsePage.export = UsePage.make();
  <ApplicationContainer page setPage />;
};
