[@bs.module "react-beautiful-dnd"]
external reactClass: ReasonReact.reactClass = "Droppable";

let make = (~droppableId: string, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={"droppableId": droppableId},
    children,
  );
