[@bs.val] external fetch: (string, Js.t({..})) => Js.Promise.t('a) = "fetch";

let getRequest =
    (
      ~url: string,
      ~accessToken: string,
      ~onSuccess: 'a => 'b,
      ~onFail: 'a => 'b,
    ) => {
  fetch(url, {
               "headers": {
                 "Authorization": {j|Bearer $accessToken|j},
               },
             })
  |> Js.Promise.then_(response => response##json())
  |> Js.Promise.then_(onSuccess)
  |> Js.Promise.catch(onFail);
};

let postRequest =
    (
      ~url: string,
      ~body: Js.t({..}),
      ~accessToken: string,
      ~onSuccess: 'a => 'b,
      ~onFail: 'a => 'b,
    ) => {
  fetch(url, {
               "headers": {
                 "Authorization": {j|Bearer $accessToken|j},
               },
             })
  |> Js.Promise.then_(response => response##json())
  |> Js.Promise.then_(onSuccess)
  |> Js.Promise.catch(onFail);
};
