module RR = ReasonReact;
let s = RR.string;
let style = ReactDOMRe.Style.make;

let reorder = (arr, index1, index2) => {
  let arr = Array.copy(arr);
  switch (arr |> Js.Array.spliceInPlace(~pos=index1, ~remove=1, ~add=[||])) {
  | [|removed|] =>
    arr
    |> Js.Array.spliceInPlace(~pos=index2, ~remove=0, ~add=[|removed|])
    |> ignore
  | _ => ()
  };
  arr;
};

let getListStyle = isDraggingOver =>
  style(
    ~background=isDraggingOver ? "lightblue" : "lightgrey",
    ~padding="1rem",
    ~width="250px",
    (),
  );

let getItemStyle = (isDragging, draggableStyle) =>
  ReactDOMRe.Style.combine(
    style(
      ~userSelect="none",
      ~padding="0.5rem 1rem",
      ~marginBottom="1rem",
      ~backgroundColor=isDragging ? "palegoldenrod" : "ivory",
      (),
    ),
    draggableStyle,
  );

type card = {
  id: string,
  content: string,
};

type state = {cards: array(card)};

type action =
  | DropCard(DragDropContext.dragResult);

let component = RR.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {
    cards:
      Array.makeBy(30, i =>
        {
          id: i->string_of_int,
          content: {js|卡片 |js} ++ (i + 1)->string_of_int,
        }
      ),
  },

  reducer: (action, state) =>
    switch (action) {
    | DropCard(result) =>
      switch (result##destination->Js.toOption) {
      | Some(destination) =>
        RR.Update({
          cards:
            state.cards->reorder(result##source##index, destination##index),
        })
      | None => RR.NoUpdate
      }
    },

  render: ({state, send}) =>
    <div>
      <h1> "Reason react-beautiful-dnd example"->s </h1>
      <DragDropContext onDragEnd={result => send @@ DropCard(result)}>
        <Droppable droppableId="droppable">
          ...{(provided, snapshot) =>
            <VariadicDiv
              props=[provided##droppableProps]
              theRef=provided##innerRef
              style={getListStyle(snapshot##isDraggingOver)}>
              {state.cards
               ->Array.mapWithIndex((index, card) =>
                   <Draggable key={card.id} draggableId={card.id} index>
                     ...{(provided, snapshot) =>
                       <VariadicDiv
                         theRef=provided##innerRef
                         props=[
                           provided##draggableProps,
                           provided##dragHandleProps,
                         ]
                         style={getItemStyle(
                           snapshot##isDragging,
                           provided##draggableProps##style,
                         )}>
                         card.content->s
                         // Show that your preferred dragging cursor will
                         // override child cursor styles
                         <span
                           style={style(
                             ~marginLeft="1rem",
                             ~cursor="pointer",
                             (),
                           )}>
                           "look at this"->s
                         </span>
                       </VariadicDiv>
                     }
                   </Draggable>
                 )
               ->RR.array}
              {provided##placeholder}
            </VariadicDiv>
          }
        </Droppable>
      </DragDropContext>
    </div>,
};
