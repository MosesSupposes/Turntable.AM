[@bs.val] external fetch: (string, Js.t({..})) => Js.Promise.t('a) = "fetch";
[@bs.module "JSON"]
external jsonStringify: Js.t({..}) => string = "stringify";

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
  fetch(
    url,
    {
      "method": "POST",
      "headers": {
        "Content-Type": "application/json",
        "Authorization": {j|Bearer $accessToken|j},
      },
      "body": jsonStringify(body),
    },
  )
  |> Js.Promise.then_(response => response##json())
  |> Js.Promise.then_(onSuccess)
  |> Js.Promise.catch(onFail);
};
