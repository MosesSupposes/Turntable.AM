[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";
[@bs.val] external encodeInBase64: string => string = "btoa";
let base = "https://api.spotify.com";
[@bs.module "uuid"] external uuid: unit => string = "v4";

module Authorization = {
  let authorizationURI = "https://accounts.spotify.com/authorize";
  let clientId = "96e25e1a56b5467fbbf82af545444904";
  let localhostEncoded = "https%3A%2F%2Flocalhost%3A1234";
  let scopes = [|"playlist-modify-public", "playlist-modify-private"|];

  // This function only encodes commas in a url
  let urlEncode = (arr: array(string)) => Js.Array.joinWith("%2C", arr);

  // The code verifier is a cryptographically random string between 43 and 128 characters. We concatenate two uuid calls together to achieve the desired length.
  let generateCodeVerifier = () => uuid() ++ uuid();

  let generateCodeChallenge = () =>
    generateCodeVerifier() |> ReCrypt.Sha256.make |> encodeInBase64;

  let signIn = () => {};
};
