type t = {
  dj: User.t,
  songs: array(Song.t),
};

let make = (~dj: User.t, ~songs: option(array(Song.t))=?, ()): t => {
  switch (songs) {
  | Some(playlist) => {dj, songs: playlist}
  | None => {dj, songs: [||]}
  };
};
