open UsePage;

[@react.component]
let make = (~setPage) => {
  <header>
    <ul>
      <li> <Link to_=Page.Home setPage> {React.string("Home")} </Link> </li>
      <li>
        <Link to_=Page.UserProfile setPage> {React.string("Profile")} </Link>
      </li>
    </ul>
  </header>;
};
