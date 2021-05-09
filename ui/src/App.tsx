import "./App.css";
import { observer } from "mobx-react";
import { ValueTree } from "./valueTree/ValueTree";

const valueTree = new ValueTree("test");

const App = observer(() => {
  return (
    <>
      <div className="App">{valueTree.type}</div>
      <button
        onClick={() => {
          valueTree.type = "test2";
          console.log(valueTree.type);
        }}
      >
        do something
      </button>
    </>
  );
});

export default App;
