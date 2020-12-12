[%bs.raw {|require("../styles/header.css")|}];
open UsePage;

[@react.component]
let make = (~setPage) => {
  <header>
    <ul className="left">
      <li>
        <Link to_=Page.Login setPage> {React.string("Sign In")} </Link>
      </li>
    </ul>
    <ul className="right">
      <li> <Link to_=Page.Home setPage> {React.string("Home")} </Link> </li>
      <li>
        <Link to_=Page.UserProfile setPage> {React.string("Profile")} </Link>
      </li>
    </ul>
  </header>;
};
