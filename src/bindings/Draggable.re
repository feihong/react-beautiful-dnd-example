[@bs.module "react-beautiful-dnd"]
external reactClass: ReasonReact.reactClass = "Draggable";

let make = (~draggableId: string, ~index: int, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={"draggableId": draggableId, "index": index},
    children,
  );
