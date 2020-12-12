[@react.component]
let make = () => {
  let {page, setPage}: UsePage.export = UsePage.make();
  <main>
    <Header setPage />
    <ApplicationContainer page setPage />
    <Footer />
  </main>;
};
