open Belt;
module RR = ReasonReact;
let s = RR.string;
let style = ReactDOMRe.Style.make;

type card = {
  id: string,
  content: string,
};

type state = {cards: array(card)};

type action =
  | MoveCard(int, int);

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
    | MoveCard(dragIndex, dropIndex) => RR.NoUpdate
    },

  render: ({state, send}) =>
    <div>
      <h1> "Cards"->s </h1>
      {state.cards
       ->Array.map(card =>
           <div
             key={card.id}
             style={style(
               ~padding="0.5rem 1rem",
               ~border="1px solid gray",
               ~marginBottom="1rem",
               ~width="300px",
               (),
             )}>
             card.content->s
           </div>
         )
       ->RR.array}
    </div>,
};
