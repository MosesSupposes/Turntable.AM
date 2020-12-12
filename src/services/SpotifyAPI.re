[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";
[@bs.val] external encodeInBase64: string => string = "btoa";
let base = "https://api.spotify.com";
[@bs.module "uuid"] external uuid: unit => string = "v4";

module Authorization = {
  let corsAnywhereUrl = "https://cors-anywhere.herokuapp.com/";
  let authorizationBaseURI = "https://accounts.spotify.com/authorize";
  let clientId = "96e25e1a56b5467fbbf82af545444904";
  let localhostEncoded = "https%3A%2F%2Flocalhost%3A1234";
  let scopes = [|
    "playlist-modify-public", // used to get write access to a user's public playlists
    "playlist-modify-private", // used to get write access to a user's private playlists
    "playlist-read-private", // used to get read access to user's private playlists
    "playlist-read-collaborative", // used to include collaborative playlists when requesting a user's playlists
    "user-read-recently-played", // used to get current user's recently played tracks
    "user-top-read", //used to get a user's top artists and tracks
    "ugc-image-upload", // used to upload a custom playlist cover image
    "user-follow-read", // used to get read access to the list of artists and other users that the user follows
    "user-library-read", // used to get read access to a user's "Your Music" library
    "user-library-modify", // used to get write/delete access to a user's "Your Music" library (can be used to save tracks + albums for current user)
    "user-read-email", // used to get read access to user's email address (can be used to get the current user's profile)
    "user-read-private" // used to get read access to a user's subscription details (type of user account) (can be used to search for an item; i.e. a song or album)
  |];

  // This function only encodes commas in a url
  let urlEncode = (arr: array(string)) => Js.Array.joinWith("%2C", arr);

  // The code verifier is a cryptographically random string between 43 and 128 characters. We concatenate two uuid calls together to achieve the desired length.
  let generateCodeVerifier = () => uuid() ++ uuid();

  let generateCodeChallenge = () =>
    generateCodeVerifier() |> ReCrypt.Sha256.make |> encodeInBase64;

  let scopesEncoded = urlEncode(scopes);
  let state = uuid();
  let codeChallenge = generateCodeChallenge();
  let authorizationURI = {j|$corsAnywhereUrl$authorizationBaseURI?response_type=code&client_id=$clientId&redirect_uri=$localhostEncoded&scope=$scopesEncoded&state=$state&code_challenge=$codeChallenge&code_challenge_method=S256|j};

  let signIn = () => {
    // fetch(authorizationURI, {"mode": "no-cors"})
    fetch(authorizationURI)
    |> Js.Promise.then_(res => Js.Promise.resolve(Js.log(res)));
  };
};
