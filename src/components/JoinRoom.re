let handleSubmit = event => {
  event.preventDefault():
  console.log("submitted");
};

[@react.component]
let make = () => {
  let (value, setValue) = React.useState(() => "")
  <form onClick={handleSubmit}><input type="text" value={value} onChange={ev => setValue(React.Synthetic##target##value)}></input><button role="submit">Enter</button></form>
};
