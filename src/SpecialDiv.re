let emptyStyle = ReactDOMRe.Style.make();

let unsafeCombineStyleProps = [%bs.raw
  {|
    function (props, style) {
      if (props.style) {
        let newStyle = {};
        Object.assign(newStyle, props.style);
        Object.assign(newStyle, style);
        props.style = newStyle;
      } else {
        props.style = style;
      }
    }
  |}
];

let component = ReasonReact.statelessComponent(__MODULE__);

let make = (~props, ~theRef, ~style=emptyStyle, children) => {
  let props =
    Belt.List.reduce(props, {"ref": theRef}, (obj, x) =>
      Js.Obj.assign(obj, x)
    );
  let _ = unsafeCombineStyleProps(props, style);
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
