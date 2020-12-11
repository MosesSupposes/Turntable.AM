[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";
let base = "https://api.spotify.com";

module Authorization = {
  let signIn = () => {};
};
