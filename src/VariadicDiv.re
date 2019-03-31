let emptyStyle = ReactDOMRe.Style.make();

let combinePropsAndStyle = (props, style) => {
  switch (props##style->Js.toOption) {
  | Some(baseStyle) =>
    props##style #= ReactDOMRe.Style.combine(baseStyle, style)
  | None => props##style #= style
  };
};

let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~props, ~theRef, ~style=emptyStyle, children) => {
  let props =
    Belt.List.reduce(props, {"ref": theRef}, (obj, x) =>
      Js.Obj.assign(obj, x)
    );
  let _ = combinePropsAndStyle(Obj.magic(props), style);
  {
    ...component,

    render: _self =>
      ReactDOMRe.createElementVariadic(
        "div",
        ~props=ReactDOMRe.objToDOMProps(props),
        children,
      ),
  };
};
