[@bs.val] external fetch: (string, Js.t({..})) => Js.Promise.t('a) = "fetch";
let request =
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
  |> Js.Promise.then_(onSuccess)
  |> Js.Promise.catch(onFail);
};
