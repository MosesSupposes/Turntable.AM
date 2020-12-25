let getRequest =
    (
      ~url: string,
      ~accessToken: string,
      ~onSuccess: Js.Promise.t('a) => Js.Promise.t('b),
      ~onFail: Js.Promise.error => Js.Promise.t('a),
    )
    : Js.Promise.t('a) => {
  let headers =
    Axios.Headers.fromObj({"Authorization": {j|Bearer $accessToken|j}});
  Js.Promise.(
    Axios.getc(url, Axios.makeConfig(~headers, ()))
    |> then_(response => resolve(response##data))
    |> then_(onSuccess)
    |> catch(onFail)
  );
};

let postRequest =
    (
      ~url: string,
      ~body: Js.t({..}),
      ~accessToken: string,
      ~onSuccess: Js.Promise.t('a) => Js.Promise.t('b),
      ~onFail: Js.Promise.error => Js.Promise.t('b),
    )
    : Js.Promise.t('a) => {
  let headers =
    Axios.Headers.fromObj({
      "Content-Type": "application/json",
      "Authorization": {j|Bearer $accessToken|j},
    });
  Js.Promise.(
    Axios.postDatac(url, body, Axios.makeConfig(~headers, ()))
    |> then_(response => resolve(response##data))
    |> then_(onSuccess)
    |> catch(onFail)
  );
};
