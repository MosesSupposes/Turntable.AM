type room =
  | Create
  | Join
  | HasntSpecified;

//TODO: pass the form control state down to the RadioButtonsGroup component so that the form coming from this parent component can communicate with its child form controls
module RadioButtonsGroup = {
  [@bs.module "./RadioButtonsGroup.js"] [@react.component]
  external make:
    (
      ~radioGroupName: string,
      ~formLabel: string,
      ~inputLabels: array(Js.t({..})),
      ~defaultValue: string,
      ~ariaLabel: string
    ) =>
    React.element =
    "default";
};

// TODO: Move the renderPlaylistEditForm logic into its own component
module Helpers = {
  let handleSubmit = event => {
    Js.log("Playlist created");
  };

  let renderPlaylistCreationForm = () =>
    <form onSubmit=handleSubmit>
      <RadioButtonsGroup
        radioGroupName="visibility"
        formLabel="Visibility"
        inputLabels=[|
          {"value": "public", "label": "Public"},
          {"value": "private", "label": "Private"},
        |]
        defaultValue="public"
        ariaLabel="Playlist visibility"
      />
      <button role="submit"> {React.string("Create")} </button>
    </form>;

  let renderRoomFinder = () => <RoomFinder />;
};

[@react.component]
let make = () => {
  let (joinOrCreateRoom, setJoinOrCreateRoom) = React.useState(() => Create);
  <div>
    <div>
      <button onClick={_ => setJoinOrCreateRoom(_ => Create)}>
        {React.string("Create a Playlist")}
      </button>
    </div>
    <div> <p> {React.string("-- Or --")} </p> </div>
    <div>
      <button onClick={_ => setJoinOrCreateRoom(_ => Join)}>
        {React.string("Edit a friend's playlist")}
      </button>
    </div>
    {switch (joinOrCreateRoom) {
     | Create => Helpers.renderPlaylistCreationForm()
     | Join => Helpers.renderRoomFinder()
     | HasntSpecified => <div />
     }}
  </div>;
  // TODO: Add a "+" icon next to the "Create a Playlist" button
  // TODO: add regular input fields for the playlist name and description
};
