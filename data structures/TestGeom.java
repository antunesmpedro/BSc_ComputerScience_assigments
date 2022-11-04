// Uma classe simples para representar um ponto 2D
class Point
{
    public int x, y;

    Point()
    {
	x = y = 0;
    }

    Point(int x, int y)
    {
	/* Para referenciar a instância do objecto que invocou o método usa-se a palavra reservada 'this' */
	this.x = x;
	this.y = y;
    }
}

class Rectangle
{
    public Point p1, p2;
  
    Rectangle()
    {
	p1 = new Point();
	p2 = new Point();
    }

    Rectangle(int x1, int y1, int x2, int y2)
    {
	p1 = new Point(x1, y1);
        p2 = new Point(x2, y2);
    }

    Rectangle(Point p1, Point p2)
    {
	this.p1 = p1;
	this.p2 = p2;
    }

    int area()
    {
	return (p2.y - p1.y) * (p2.x - p1.x);
    }

    int perimeter()
    {
	return (p2.y-p1.y) * 2 + (p2.x-p1.x) * 2; 
    }

    boolean pointInside(Point p)
    {
	if((p.x <= p2.x && p.x >= p1.x) && (p.y <= p2.y && p.y >= p1.y))
	{
	    return true;
	}

	return false;
    }

    boolean rectangleInside(Rectangle r)
    {
	return (pointInside(r.p1) && pointInside(r.p2));
    }
}

public class TestGeom
{
    public static void main (String[] args)
    {
	Point p1 = new Point();

	System.out.println("Ponto 1: " + p1.x + "," + p1.y);
	p1.x = 1;
	p1.y = 1;
	System.out.println("Ponto 1: " + p1.x + "," + p1.y);

	Point p2 = new Point(3,4);
	System.out.println("Ponto 2: " + p2.x + "," + p2.y);


	Rectangle amarelo  = new Rectangle(p1, p2);
	Rectangle laranja  = new Rectangle(2, 3, 9, 6);
	Rectangle verde    = new Rectangle(3, 4, 4, 5);
	Rectangle azul     = new Rectangle(5, 1, 6, 5);
	Rectangle vermelho = new Rectangle(7, 3, 9, 5);

	Point b = new Point(2,2);
	Point d = new Point(8,2);
	
	System.out.println("Perimetro do retangulo amarelo = " + amarelo.perimeter());
	System.out.println("Perimetro do retangulo laranja = " + laranja.perimeter());

	System.out.println("Area do retangulo amarelo = " + amarelo.area());
	System.out.println("Area do retangulo laranja = " + laranja.area());

	System.out.println("Ponto B dentro rectangulo amarelo? " + amarelo.pointInside(b));
	System.out.println("Ponto D dentro rectangulo amarelo? " + amarelo.pointInside(d));

	System.out.println("Retangulo verde dentro do laranja? " + laranja.rectangleInside(verde));
	System.out.println("Retangulo azul dentro do laranja? " + laranja.rectangleInside(azul));
    }
}
