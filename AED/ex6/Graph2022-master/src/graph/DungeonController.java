package graph;

import javax.swing.*;
import java.util.List;
import java.util.Scanner;

public class DungeonController {

    //declaro um grafo com nome dungeon
    //nao declarou pq n deu new
    private AbstractGraph dungeon;

    private static final int TOTAL_LOCKS = 3;
    //variavel do tipo room
    private Room entrance;
    private Room exit;

  //toda main tem que ser static
    public static void main(String[] args) {
        //cria um objeto do tipo dungeonController
        DungeonController dungeonController = new DungeonController();
        //cria passando o objeto que acabei de criar
        createRandomDungeon(dungeonController);

        //chama funcao triangulation
        //triangula os vertices do grafo
        //fazer triangulacao dosvertices
        DelaunayTriangulation.triangulateGraphVertices(dungeonController.dungeon);

        //
        ReplaceDungeonWithMST(dungeonController);

        //cria salas especiais, vai no grafo de dungeon e seta as salas especiais
        //define o meio, inicio e saida 
        setSpecialRooms(dungeonController);

        //cria uma lista de vertices que será o caminho
        //cria o melhor caminho da entrada a saida
        List<Vertex> traversalPath = getPathFromEntranceToExit(dungeonController);
        //os vertices vão ter chaves e fechaduras, pra passar pelas portas preciso buscar as chaves
        // nos devidos vertices
        //>> sortear salar aleatorias para guardas chaves e fechaduras
        setLocksAndKeys(dungeonController);
        //biblioteca do java que printa grafo, dungeon e o caminho a ser percorrido
        SwingUtilities.invokeLater(() -> new DungeonGraphic(dungeonController.dungeon, traversalPath).setVisible(true));
    }

    //>> sortear salar aleatorias para guardas chaves e fechaduras
    private static void setLocksAndKeys(DungeonController dungeonController)
    {
        AbstractGraph dungeon = dungeonController.dungeon;
        TraversalStrategy traversalStrategy;
        traversalStrategy = new KeyLockGenerator(dungeon, TOTAL_LOCKS);
        traversalStrategy.traverseGraph(dungeonController.entrance);
    }

    private static void createRandomDungeon(DungeonController dungeonController)
    {
        System.out.println("What will be the random seed?");
        //pra ler do teclado
        Scanner scanner = new Scanner(System.in);
        //pega a semente
        int seed = Integer.parseInt(scanner.nextLine());
        //gera um numero aleatorio e passa a seed
        RandomSingleton.getInstance(seed);
        System.out.println("How many rooms will the dungeon have?");
        //input no numero de salas 
        int nRooms = Integer.parseInt(scanner.nextLine());
        //cria os retangulos que representam os vertices
        var randomDungeonGenerator = new DungeonGenerator(nRooms);
        dungeonController.dungeon = randomDungeonGenerator.getDungeon();
    }

    //
    private static void  ReplaceDungeonWithMST(DungeonController dungeonController)
    {
        AbstractGraph dungeon = dungeonController.dungeon;
        TraversalStrategy traversalStrategy;
        traversalStrategy = new PrimMSTTraversal(dungeon);
        traversalStrategy.traverseGraph(dungeon.getVertices().get(0));
        dungeonController.dungeon = GraphConverter.predecessorListToGraph(dungeon, traversalStrategy.getPredecessorArray());
    }

    private static void setSpecialRooms(DungeonController dungeonController)
    {   //cria grafo do tipo dungeon
        AbstractGraph dungeon = dungeonController.dungeon;
        //retorna matriz/grafo floyd warshall de distancia 
        //percorre o grafo = traversal
        TraversalStrategy traversalStrategy = new FloydWarshallTraversal(dungeon);
        traversalStrategy.traverseGraph(dungeon.getVertices().get(0));
        //entrada
        Room center = (Room) dungeon.getCentermostVertex(((FloydWarshallTraversal)traversalStrategy).getDistanceMatrix());
        center.setCheckPoint(true);
        
        //O vertice mais distante do vertice mais distante
        Room entrance = (Room) dungeon.getOuterMostVertex(((FloydWarshallTraversal)traversalStrategy).getDistanceMatrix());
        entrance.setEntrance(true);
        dungeonController.entrance = entrance;

        //vertice mais periferico
        Room exit = (Room) dungeon.getMostDistantVertex(((FloydWarshallTraversal)traversalStrategy).getDistanceMatrix(), entrance);
        exit.setExit(true);
        dungeonController.exit = exit;
    }

    private static List<Vertex> getPathFromEntranceToExit(DungeonController dungeonController)
    {
        AbstractGraph dungeon = dungeonController.dungeon;
        TraversalStrategy aStar = new AStarPathFind(dungeon);
        aStar.traverseGraph(dungeonController.entrance, dungeonController.exit);
        return aStar.getShortestPath(dungeonController.entrance, dungeonController.exit);
    }
}
