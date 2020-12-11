type t = {
  dj: User.t,
  songs: list(Song.t),
};

let make = (~dj: User.t, ~songs: option(list(Song.t))=?, ()): t => {
  switch (songs) {
  | Some(playlist) => {dj, songs: playlist}
  | None => {dj, songs: []}
  };
};
