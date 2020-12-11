type t = {
  id: string,
  username: string,
  // currentRoom: option(Room.t), // this causes a cyclic dependency
  friends: list(t),
  avatarUrl: option(string),
  preferredTheme: Theme.t,
};

// TODO: update these records in the database

let changeTheme = (theme: Theme.t, user: t): t => {
  {...user, preferredTheme: theme};
};

let addFriend = (friend: t, user: t): t => {
  {...user, friends: [friend, ...user.friends]};
};

let removeFriend = (friend: t, user: t): t => {
  {...user, friends: List.filter(f => f.id != friend.id, user.friends)};
};
