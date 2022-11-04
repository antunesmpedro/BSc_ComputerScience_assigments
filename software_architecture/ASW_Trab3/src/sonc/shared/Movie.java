package sonc.shared;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
//import game.Players;
//import utils.WorldViewer;

/**
 * Data for an animation of the game that can be presented to the player. It is composed of a sequence of frames, each
 * with a sequence of oblong objects and another of player's scores. Oblong objects of different sizes and colors represent
 * ships and munitions.
 * @author
 */

public class Movie implements Serializable {
	
	private static final long serialVersionUID = 1L;
	/**
	* class variables definition
	*/
	
	List<Movie.Frame> frames;
	int currentFrame;
	
	public static class Oblong {

		/**
		* class variables definition
		*/
		String color;
		float heading;
		int size;
		int x;
		int y;
		
		public Oblong() {}

		public Oblong(int x, int y, float heading, int size, String color){
			super();
			this.color = color;
			this.heading = heading;
			this.size = size;
			this.x = x;
			this.y = y;
		}


		/**
		 * Getters 
		 */
		public int getX(){	return this.x;  }
		public int getY(){  return this.y;	}
		public float getHeading(){  return this.heading; }
		public int getSize(){  return this.size;  }
		public String getColor(){  return this.color;  }
	}
	public static class Score {

		/**
		* class variables definition
		*/
		String name;
		int points;
		int status;
		
		public Score(String name, int points, int status) {
			super();
			this.name = name;
			this.points = points;
			this.status = status;
		}
		
		/**
		 * Getters
		 */
		public String getName() {  return this.name;  }
		public int getPoints() {  return this.points;  }
		public int getStatus() {  return this.status;  }
	}
	public static class Frame {
		
		/**
		* class variables definition
		*/
		List<Movie.Oblong> oblongs;
		List<Movie.Score> scores;
		
		public Frame() {
			super();
			this.oblongs = new ArrayList<Movie.Oblong>(); 
			this.scores = new ArrayList<Movie.Score>();
		}
		
		/**
		 * Getters
		 */
		public List<Movie.Oblong> getOblongs() {
			return this.oblongs;
		}
		
		public List<Movie.Score> getScores() {
			return this.scores;
		}
	}
	
	/**
	 * Creates one sequence of frames into one movie(animation) 
	 */
	public Movie(){
		this.frames = new ArrayList<Movie.Frame>();
		currentFrame = 0;
	}
	
	/**
	 * --- SETTERS ----
	 * 
	 * Create a new frame. Subsequent calls to addOblong() or addScore() will add elements to this frame
	 * Increments index of currentFrame
	 */
	
	public void newFrame() {
		Frame frame = new Frame();
		frames.add(frame);
		this.addOblong(500,500,90,50,"pink");		//data ??
		this.addScore("nick",1000,1);			//data ?
		currentFrame++;
	}
	
	/**
	 * Add a Oblong to current frame
	 * 
	 * @param x coordinate of object
	 * @param y coordinate of object
	 * @param heading of object (angle in radians)
	 * @param size of oblong shape
	 * @param color String with its name (e.g. "red") or HTML/CSS format (e.g. "#FF0000")
	 * @throws IllegalStateException if no frame was created before
	 */
	public void addOblong(int x, int y, float heading, int size, String color) {
		if(frames.get(currentFrame) == null)
			throw new IllegalStateException("Cannot add a rect before creating a frame");
		else
			frames.get(currentFrame).oblongs.add(new Oblong(x,y,heading, size, color));
	}
	
	/**
	 * Add a score to current frame
	 * 
	 * @param name  of player
	 * @param points of player
	 * @param status of player
	 * @throws IllegalStateException if no frame was created
	 */
	public void addScore(String name,int points, int status) {
		if(frames.get(currentFrame) == null)
			throw new IllegalStateException("Cannot add a score before creating a frame");
		else
			frames.get(currentFrame).scores.add(new Score(name, points, status));
	}
	
	/**
	 *  ----GETTERS----
	 * 
	 * The list of frames
	 * @return frames
	 */
	public List<Movie.Frame> getFrames() {
		return frames;
	}
}
