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
      ~backgroundColor=isDragging ? "firebrick" : "grey",
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
  | MoveCard(int, int)
  | DropCard(DragDropContext.dragResult);

let component = RR.reducerComponent(__MODULE__);

let make = _children => {
  ...component,

  initialState: () => {
    cards:
      Array.makeBy(10, i =>
        {id: i->string_of_int, content: "item " ++ (i + 1)->string_of_int}
      ),
  },

  reducer: (action, state) =>
    switch (action) {
    | DropCard(result) =>
      RR.SideEffects(
        ({send}) =>
          result##destination
          ->Js.toOption
          ->Option.map(destination =>
              send @@ MoveCard(result##source##index, destination##index)
            )
          ->ignore,
      )
    | MoveCard(dragIndex, dropIndex) =>
      RR.Update({cards: state.cards->reorder(dragIndex, dropIndex)})
    },

  render: ({state, send}) =>
    <div>
      <h1> "Cards"->s </h1>
      <DragDropContext onDragEnd={result => send @@ DropCard(result)}>
        <Droppable droppableId="droppable">
          ...{(provided, snapshot) =>
            <SpecialDiv
              props=[provided##droppableProps]
              theRef=provided##innerRef
              style={getListStyle(snapshot##isDraggingOver)}>
              {state.cards
               ->Array.mapWithIndex((index, card) =>
                   <Draggable key={card.id} draggableId={card.id} index>
                     ...{(provided, snapshot) =>
                       <SpecialDiv
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
                       </SpecialDiv>
                     }
                   </Draggable>
                 )
               ->RR.array}
              {provided##placeholder}
            </SpecialDiv>
          }
        </Droppable>
      </DragDropContext>
    </div>,
};
