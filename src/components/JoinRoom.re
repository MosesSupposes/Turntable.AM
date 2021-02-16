let handleSubmit = event => {
  ReactEvent.Mouse.preventDefault(event);
  Js.log("submitted");
};

[@react.component]
let make = () => {
  let (value, setValue) = React.useState(() => "");
  <form onClick=handleSubmit>
    <input
      type_="text"
      value
      onChange={event => setValue(ReactEvent.Form.target(event)##value)}
    />
    <button role="submit"> {React.string("Enter")} </button>
  </form>;
};
