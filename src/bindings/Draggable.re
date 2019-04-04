[@bs.module "react-beautiful-dnd"]
external reactClass: ReasonReact.reactClass = "Draggable";

let make =
    (~draggableId: string, ~index: int, ~isDragDisabled: bool, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={
      "draggableId": draggableId,
      "isDragDisabled": isDragDisabled,
      "index": index,
    },
    children,
  );
