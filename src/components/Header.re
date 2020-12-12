open UsePage;

[@react.component]
let make = (~setPage) => {
  <header>
    <ul>
      <li onClick={_ => setPage(_ => Page.Home)}> {React.string("Home")} </li>
      <li onClick={_ => setPage(_ => Page.UserProfile)}>
        {React.string("Profile")}
      </li>
    </ul>
  </header>;
};
