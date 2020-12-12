[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";
[@bs.val] external encodeInBase64: string => string = "btoa";
let base = "https://api.spotify.com";

module Authorization = {
  let authorizationURI = "https://accounts.spotify.com/authorize";
  let clientId = "96e25e1a56b5467fbbf82af545444904";
  let localhostEncoded = "https%3A%2F%2Flocalhost%3A1234";

  let signIn = () => {};
};
