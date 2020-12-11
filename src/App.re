[@react.component]
let app = () => {
  let {page, setPage}: UsePage.export = UsePage.make();
  <ApplicationContainer page setPage />;
};
