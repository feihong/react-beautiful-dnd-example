[@bs.module "react-beautiful-dnd"]
external reactClass: ReasonReact.reactClass = "DragDropContext";

type dragSource = {. "index": int};

type dragDestination = {. "index": int};

type dragResult = {
  .
  "source": dragSource,
  "destination": Js.nullable(dragDestination),
};

let make = (~onDragEnd: dragResult => unit, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={"onDragEnd": onDragEnd},
    children,
  );
